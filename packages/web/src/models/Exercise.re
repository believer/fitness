type equipment = [
  | `SkiErg
  | `Rower
  | `Barbell
  | `Kettlebell
  | `Dumbbell
  | `Curlbar
  | `BulgarianBag
  | `Bodyweight
];

type t = {
  id: string,
  exerciseId: string,
  equipment,
  reps: int,
  weight: option(float),
  name: string,
};

let make = (~id, ~exerciseId, ~reps, ~weight, ~name, ~equipment) => {
  id,
  exerciseId,
  reps,
  weight,
  name,
  equipment,
};

let toUnitType =
  fun
  | `SkiErg
  | `Rower => "kcal"
  | _ => "reps";

let toEquipmentType =
  fun
  | `Barbell => Some("Barbell")
  | `Dumbbell => Some("Dumbbell")
  | `Kettlebell => Some("Kettlebell")
  | `Curlbar => Some("Curlbar")
  | _ => None;

let toReps = (reps, equipment) =>
  reps->string_of_int ++ " " ++ equipment->toUnitType;
let toWeight = weight => weight->Js.Float.toString ++ " kg";

let withReps = ({reps, weight, equipment}) => {
  switch (weight) {
  | Some(weight) => toReps(reps, equipment) ++ " @ " ++ weight->toWeight
  | None => toReps(reps, equipment)
  };
};
