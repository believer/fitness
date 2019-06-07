module Style = {
  open Css;

  let row =
    style([
      borderBottom(`px(1), `solid, Theme.Colors.graySuit),
      display(`grid),
      gridColumnGap(`px(20)),
      gridTemplateColumns([`px(40), `px(80), `fr(1.0)]),
      padding2(~v=`px(10), ~h=`zero),
    ]);
};

let unitValue = (equipment, weight) =>
  switch (equipment, weight) {
  | (`SkiErg, None)
  | (`Rower, None) => " kcal"
  | (`Bodyweight, None) => " st"
  | (_, Some(_)) => " kg"
  | (_, None) => ""
  };

let equipmentType =
  fun
  | `Barbell => "Barbell"
  | `Dumbbell => "Dumbbell"
  | _ => "";

[@react.component]
let make = (~exercise) => {
  <div className=Style.row>
    <div className="tr"> {exercise##reps->string_of_int->React.string} </div>
    <div className="gray">
      {switch (exercise##weight) {
       | Some(weight) => weight->Js.Float.toString->React.string
       | None => React.null
       }}
      {unitValue(exercise##exercise##equipment, exercise##weight)
       ->React.string}
    </div>
    <div>
      {exercise##exercise##equipment->equipmentType
       ++ " "
       ++
       exercise##exercise##name
       |> React.string}
    </div>
  </div>;
};
