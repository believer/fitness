module GetExercise = [%graphql
  {|
  query allWodsWithExercise($exerciseId: ID!) {
    allWodsWithExercise(exerciseId: $exerciseId) {
      id
      exerciseId
      name
      weight
      reps
      equipment
    }
  }
|}
];

module GetExerciseQuery = ReasonApollo.CreateQuery(GetExercise);

[@react.component]
let make = (~id) => {
  let variables = GetExercise.make(~exerciseId=id, ())##variables;

  <GetExerciseQuery variables>
    {({result}) =>
       switch (result) {
       | Loading => <div> {React.string("Loading")} </div>
       | Error(error) => <div> {React.string(error##message)} </div>
       | Data(response) =>
         let exercises = response##allWodsWithExercise->Belt.List.fromArray;

         <Wrapper>
           {switch (exercises) {
            | [first, ..._tail] =>
              <Typography.H1 className="font-semibold mt-0 mb-3">
                {first##name->React.string}
              </Typography.H1>
            | [] => React.null
            }}
           {exercises
            ->Belt.List.map(exercise =>
                Exercise.make(
                  ~name=exercise##name,
                  ~reps=exercise##reps,
                  ~weight=exercise##weight,
                  ~equipment=exercise##equipment,
                  ~id=exercise##id,
                  ~exerciseId=exercise##exerciseId,
                )
              )
            ->Belt.List.map(exercise =>
                <ExerciseBlock exercise key={exercise.id} />
              )
            ->Belt.List.toArray
            ->React.array}
         </Wrapper>;
       }}
  </GetExerciseQuery>;
};
