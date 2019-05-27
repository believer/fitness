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

  let reps = style([textAlign(`right)]);

  let weight = style([color(Theme.Colors.manatee)]);
};

let unitValue = (equipment, weight) =>
  switch (equipment, weight) {
  | (`SKI_ERG, None)
  | (`ROWER, None) => " kcal"
  | (`BODYWEIGHT, None) => " st"
  | (_, Some(_)) => " kg"
  | (_, None) => ""
  };

let equipmentType =
  fun
  | `BARBELL => "Barbell"
  | `DUMBBELL => "Dumbbell"
  | _ => "";

[@react.component]
let make = (~exercise) => {
  <div className=Style.row>
    <div className=Style.reps>
      {exercise##reps->string_of_int->React.string}
    </div>
    <div className=Style.weight>
      {switch (exercise##weight) {
       | Some(weight) => weight->Js.Float.toString->React.string
       | None => React.null
       }}
      {switch (exercise##exerciseByExerciseId) {
       | Some(e) => unitValue(e##equipment, exercise##weight) |> React.string
       | None => React.null
       }}
    </div>
    {switch (exercise##exerciseByExerciseId) {
     | Some(e) =>
       <div>
         {e##equipment->equipmentType ++ " " ++ e##name |> React.string}
       </div>
     | None => React.null
     }}
  </div>;
};
