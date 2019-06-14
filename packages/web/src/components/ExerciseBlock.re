[@react.component]
let make = (~exercise: Exercise.t) => {
  <div className="flex py-2 text-sm border-b border-gray-400 items-center">
    <div className="font-semibold"> {exercise.name |> React.string} </div>
    <div className="text-gray-500 ml-3">
      {Exercise.withReps(exercise) |> React.string}
      {switch (exercise.equipment->Exercise.toEquipmentType) {
       | Some(eq) => {j| • |j} ++ eq |> React.string
       | None => React.null
       }}
    </div>
  </div>;
};
