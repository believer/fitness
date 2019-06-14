module GetWODs = [%graphql
  {|
  query wodById($id: ID!) {
    wodById(id: $id) {
      id
      totalWeight
      createdAt
      name
      exercises {
        id
        reps
        weight
        exercise {
          id
          name
          equipment
        }
      }
    }
  }
|}
];

module GetWODsQuery = ReasonApollo.CreateQuery(GetWODs);

[@react.component]
let make = (~id) => {
  let variables = GetWODs.make(~id, ())##variables;

  <GetWODsQuery variables>
    {({result}) =>
       switch (result) {
       | Loading => <div> "Loading"->React.string </div>
       | Error(error) => <div> {error##message->React.string} </div>
       | Data(response) =>
         switch (response##wodById) {
         | Some(wod) =>
           let {totalWeight, name, createdAt}: Workout.t = Workout.make(wod);

           <Wrapper>
             <div className="flex items-start">
               <DateTime date=createdAt />
               <div className="ml-6">
                 <Typography.H1 className="font-semibold mt-0 mb-4">
                   name->React.string
                 </Typography.H1>
                 {wod##exercises
                  ->Belt.Array.map(exercise =>
                      Exercise.make(
                        ~id=exercise##id,
                        ~exerciseId=exercise##exercise##id,
                        ~reps=exercise##reps,
                        ~weight=exercise##weight,
                        ~name=exercise##exercise##name,
                        ~equipment=exercise##exercise##equipment,
                      )
                    )
                  ->Belt.Array.map(exercise =>
                      <Router.Link
                        href={"/exercise/" ++ exercise.exerciseId}
                        key={exercise.id}>
                        <ExerciseBlock exercise />
                      </Router.Link>
                    )
                  ->React.array}
                 <div className="text-gray-500 mt-2 text-sm">
                   {Exercise.toWeight(totalWeight)->React.string}
                 </div>
               </div>
             </div>
           </Wrapper>;
         | None => React.null
         }
       }}
  </GetWODsQuery>;
};
