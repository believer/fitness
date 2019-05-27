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

  let workoutHeader = style([marginBottom(`px(30))]);

  let workoutTitle = style([marginBottom(`px(10))]);

  let totalWeight = style([color(Theme.Colors.manatee), padding(`px(10))]);
};

module GetWODs = [%graphql
  {|
  query wodById($id: Int!) {
    wodById(id: $id) {
      id
      totalWeight
      createdAt
      name
      wodExercisesByWodId {
        nodes {
          id
          reps
          weight
          exerciseByExerciseId {
            id
            name
            equipment
          }
        }
      }
    }
  }
|}
];

module GetWODsQuery = ReasonApollo.CreateQuery(GetWODs);

[@react.component]
let make = (~id) => {
  let wodQuery = GetWODs.make(~id=id->int_of_string, ());

  <GetWODsQuery variables=wodQuery##variables>
    ...{({result}) =>
      switch (result) {
      | Loading => <div> "Loading"->React.string </div>
      | Error(error) => <div> {error##message->React.string} </div>
      | Data(response) =>
        switch (response##wodById) {
        | Some(wod) =>
          let exercises = wod##wodExercisesByWodId##nodes;

          <div className=Style.workouts>
            <div className=Style.workout key={wod##id->string_of_int}>
              <header className=Style.workoutHeader>
                {switch (wod##name) {
                 | Some(name) =>
                   <Typography.H2 className=Style.workoutTitle>
                     name->React.string
                   </Typography.H2>
                 | None => React.null
                 }}
                <Typography.H3>
                  <DateTime date=wod##createdAt />
                </Typography.H3>
              </header>
              {exercises
               ->Belt.Array.keepMap(node => node)
               ->Belt.Array.map(exercise =>
                   <Exercise exercise key={exercise##id->string_of_int} />
                 )
               ->React.array}
              <div className=Style.totalWeight>
                {wod##totalWeight
                 ->Belt.Option.getWithDefault(0.0)
                 ->Js.Float.toString
                 ++ " kg"
                 |> React.string}
              </div>
            </div>
          </div>;
        | None => React.null
        }
      }
    }
  </GetWODsQuery>;
};
