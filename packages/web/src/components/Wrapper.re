module Style = {
  open Css;

  let workouts =
    style([
      display(`grid),
      gridTemplateColumns([`fr(1.0), `px(800), `fr(1.0)]),
      marginBottom(`px(100)),
      marginTop(`px(100)),
    ]);

  let workout =
    style([
      gridColumn(2, 2),
      selector(":not(:last-of-type)", [marginBottom(`px(40))]),
    ]);
};

[@react.component]
let make = (~children) => {
  <div className=Style.workouts>
    <div className=Style.workout> children </div>
  </div>;
};
