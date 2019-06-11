let unitType =
  fun
  | `SkiErg
  | `Rower => "kcal"
  | _ => "reps";

let equipmentType =
  fun
  | `Barbell => Some("Barbell")
  | `Dumbbell => Some("Dumbbell")
  | `Kettlebell => Some("Kettlebell")
  | `Curlbar => Some("Curlbar")
  | _ => None;

[@react.component]
let make = (~exercise) => {
  <div className="flex pv2 f7 bb b--moon-gray items-center">
    <div className="fw6"> {exercise##exercise##name |> React.string} </div>
    <div className="gray ml3">
      {(
         switch (exercise##weight) {
         | Some(weight) =>
           exercise##reps->string_of_int
           ++ " reps @ "
           ++ weight->Js.Float.toString
           ++ " kg"
         | None =>
           exercise##reps->string_of_int
           ++ " "
           ++ unitType(exercise##exercise##equipment)
         }
       )
       |> React.string}
      {switch (exercise##exercise##equipment->equipmentType) {
       | Some(eq) => {j| • |j} ++ eq |> React.string
       | None => React.null
       }}
    </div>
  </div>;
};
