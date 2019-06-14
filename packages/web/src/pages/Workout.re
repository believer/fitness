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
      alignItems(`flexStart),
      display(`grid),
      gridColumn(2, 2),
      gridColumnGap(`px(30)),
      gridTemplateColumns([`auto, `fr(1.0)]),
      selector(":not(:last-of-type)", [marginBottom(`px(40))]),
    ]);
};

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
           <div className=Style.workouts>
             <div className=Style.workout key=wod##id>
               <DateTime date=wod##createdAt />
               <div>
                 <header className="mb-4">
                   <Typography.H1 className="font-semibold mt-0 mb-1">
                     {switch (wod##name) {
                      | Some(name) => name->React.string
                      | None =>
                        wod##exercises
                        ->Belt.Array.slice(~offset=0, ~len=3)
                        ->Belt.Array.map(exercise => exercise##exercise##name)
                        |> Js.Array.joinWith(", ")
                        |> React.string
                      }}
                   </Typography.H1>
                 </header>
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
                      <Router.Link href={"/exercise/" ++ exercise.exerciseId}>
                        <ExerciseBlock exercise key={exercise.id} />
                      </Router.Link>
                    )
                  ->React.array}
                 <div className="text-gray mt-2">
                   {wod##totalWeight
                    ->Belt.Option.getWithDefault(0.0)
                    ->Js.Float.toString
                    ++ " kg"
                    |> React.string}
                 </div>
               </div>
             </div>
           </div>
         | None => React.null
         }
       }}
  </GetWODsQuery>;
};
