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
      gridColumn(2, 2),
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
               <header className="mb3">
                 {switch (wod##name) {
                  | Some(name) =>
                    <Typography.H2 className="mb2">
                      name->React.string
                    </Typography.H2>
                  | None => React.null
                  }}
                 <Typography.H3>
                   <DateTime date=wod##createdAt />
                 </Typography.H3>
               </header>
               {wod##exercises
                ->Belt.Array.map(exercise =>
                    <Exercise exercise key=exercise##id />
                  )
                ->React.array}
               <div className="gray pa2">
                 {wod##totalWeight
                  ->Belt.Option.getWithDefault(0.0)
                  ->Js.Float.toString
                  ++ " kg"
                  |> React.string}
               </div>
             </div>
           </div>
         | None => React.null
         }
       }}
  </GetWODsQuery>;
};
