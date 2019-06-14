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
};

[@react.component]
let make = (~workout) => {
  switch (workout) {
  | Some(w) =>
    <Router.Link
      className="block pb-2 border-b border-gray-400"
      href={"/workout/" ++ w##id}>
      <div className=Style.card>
        <div className="rounded bg-blue-500 text-white p-3 my-3 relative z-20">
          <div className="text-sm mb-2 text-blue-200">
            "Latest workout"->React.string
          </div>
          <Typography.H3 className="font-semibold mt-0 mb-1">
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
          <div className="text-sm text-blue-200">
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
