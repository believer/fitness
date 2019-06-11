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
                 <header className="mb3">
                   <Typography.H1 className="fw6 mt0 mb1">
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
                      <Exercise exercise key=exercise##id />
                    )
                  ->React.array}
                 <div className="gray mt2">
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
