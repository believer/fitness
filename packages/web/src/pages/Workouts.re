module Style = {
  open Css;

  let workouts =
    style([
      display(`grid),
      gridTemplateColumns([`fr(1.0), `px(600), `fr(1.0)]),
      marginTop(`px(100)),
      selector("> div", [gridColumn(2, 2)]),
    ]);
};

module GetAllWODs = [%graphql
  {|
    query allWods {
      allWods {
        id
        createdAt
        name
      }
    }
 |}
];

module GetAllWODsQuery = ReasonApollo.CreateQuery(GetAllWODs);

[@react.component]
let make = () => {
  <div className=Style.workouts>
    <GetAllWODsQuery>
      ...{({result}) =>
        switch (result) {
        | Loading => <div> "Loading"->React.string </div>
        | Error(error) => <div> {error##message->React.string} </div>
        | Data(response) =>
          <div>
            Belt.(
              response##allWods
              ->Array.map(wod =>
                  <Router.Link href={"/workout/" ++ wod##id} key=wod##id>
                    <DateTime date=wod##createdAt />
                    {wod##name->Option.getWithDefault("")->React.string}
                  </Router.Link>
                )
              ->React.array
            )
          </div>
        }
      }
    </GetAllWODsQuery>
  </div>;
};
