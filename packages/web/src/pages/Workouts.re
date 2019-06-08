module Style = {
  open Css;

  let workouts =
    style([
      display(`grid),
      gridTemplateColumns([`px(20), `fr(1.0), `px(20)]),
      marginTop(`px(100)),
      selector("> div", [gridColumn(2, 2)]),
      media(
        "(min-width: 768px)",
        [gridTemplateColumns([`fr(1.0), `px(600), `fr(1.0)])],
      ),
    ]);
};

module GetAllWODs = [%graphql
  {|
    query allWods {
      allWods {
        id
        createdAt
        name
        totalWeight
        exercises {
          id
          exercise {
            name
          }
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
          let wods = response##allWods;
          let totalWeight =
            wods->Belt.Array.reduce(0.0, (a, b) =>
              a +. b##totalWeight->Belt.Option.getWithDefault(0.0)
            );

          <div>
            <div className="flex bb b--moon-gray">
              <div className="w-50 pa3 br b--moon-gray">
                <div className="f3">
                  {wods->Belt.Array.length->string_of_int->React.string}
                </div>
                <div className="gray mt1 f7">
                  "workouts completed"->React.string
                </div>
              </div>
              <div className="w-50 pa3">
                <div className="f3">
                  {switch (totalWeight) {
                   | w when w > 1000.0 =>
                     (w /. 1000.0)->Js.Float.toString->React.string
                   | w => w->Js.Float.toString->React.string
                   }}
                </div>
                <div className="gray mt1 f7">
                  {switch (totalWeight) {
                   | w when w > 1000.0 =>
                     <div> "tons lifted"->React.string </div>
                   | _ => <div> "kgs lifted"->React.string </div>
                   }}
                </div>
              </div>
            </div>
            <LatestWorkout workout={wods->Belt.Array.get(0)} />
            Belt.(
              wods
              ->Array.sliceToEnd(1)
              ->Array.map(wod =>
                  <Router.Link
                    className="flex items-center pa3 bb b--moon-gray grow"
                    href={"/workout/" ++ wod##id}
                    key=wod##id>
                    <DateTime date=wod##createdAt />
                    <div className="ml3">
                      <Typography.H3 className="fw6 mt0 mb1">
                        {switch (wod##name) {
                         | Some(name) => name->React.string
                         | None =>
                           wod##exercises
                           ->Belt.Array.slice(~offset=0, ~len=3)
                           ->Belt.Array.map(exercise =>
                               exercise##exercise##name
                             )
                           |> Js.Array.joinWith(", ")
                           |> React.string
                         }}
                      </Typography.H3>
                      <div className="f7 gray">
                        {switch (wod##exercises->Belt.Array.length) {
                         | 0 => React.null
                         | 1 => "1 exercise completed"->React.string
                         | v =>
                           v->string_of_int
                           ++ " exercises completed"
                           |> React.string
                         }}
                      </div>
                    </div>
                  </Router.Link>
                )
              ->React.array
            )
          </div>;
        }
      }
    </GetAllWODsQuery>
  </div>;
};
