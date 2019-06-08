[@react.component]
let make = (~date) => {
  let formattedDate = date |> Js.Float.fromString |> Js.Date.fromFloat;

  <div className="bg-blue white ph2 pv2 br2 tc">
    <div className="f4 fw6">
      {formattedDate |> DateFns.format("DD") |> React.string}
    </div>
    <div className="f7 fw3 ttu">
      {formattedDate |> DateFns.format("MMM") |> React.string}
    </div>
  </div>;
};
