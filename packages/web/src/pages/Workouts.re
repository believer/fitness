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
      allWods(orderBy: CREATED_AT_DESC) {
        nodes {
          id
          createdAt
          name
        }
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
              [%get_in
                response##allWods#?nodes
                ->Option.getWithDefault([||])
                ->Array.keepMap(node => node)
              ]
              ->Array.map(node =>
                  <Router.Link
                    href={"/workout/" ++ node##id->string_of_int}
                    key={node##id->string_of_int}>
                    <DateTime date=node##createdAt />
                    {node##name->Option.getWithDefault("")->React.string}
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
