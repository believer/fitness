module Style = {
  open Css;

  let card =
    merge([
      "relative",
      style([
        after([
          backgroundColor(`hex("357EDD66")),
          borderRadius(`rem(0.125)),
          bottom(`px(-5)),
          contentRule(""),
          height(`percent(100.0)),
          left(`px(10)),
          position(`absolute),
          right(`px(10)),
          zIndex(2),
        ]),
        before([
          backgroundColor(`hex("96CCFF66")),
          borderRadius(`rem(0.125)),
          bottom(`px(-10)),
          contentRule(""),
          height(`percent(100.0)),
          left(`px(20)),
          position(`absolute),
          right(`px(20)),
          zIndex(1),
        ]),
      ]),
    ]);

  let cardContent =
    merge([
      "br1 bg-blue white pa3 mv3 relative",
      style([zIndex(4), position(`relative)]),
    ]);
};

[@react.component]
let make = (~workout) => {
  switch (workout) {
  | Some(w) =>
    <Router.Link
      className="db pb2 bb b--moon-gray" href={"/workout/" ++ w##id}>
      <div className=Style.card>
        <div className=Style.cardContent>
          <div className="f7 mb2 lightest-blue">
            "Latest workout"->React.string
          </div>
          <Typography.H3 className="fw6 mt0 mb1">
            {switch (w##name) {
             | Some(name) => name->React.string
             | None =>
               w##exercises
               ->Belt.Array.slice(~offset=0, ~len=3)
               ->Belt.Array.map(exercise => exercise##exercise##name)
               |> Js.Array.joinWith(", ")
               |> React.string
             }}
          </Typography.H3>
          <div className="f7 lightest-blue">
            {w##createdAt
             |> Js.Float.fromString
             |> Js.Date.fromFloat
             |> DateFns.format("dddd, MMMM D")
             |> React.string}
          </div>
        </div>
      </div>
    </Router.Link>
  | None => React.null
  };
};
