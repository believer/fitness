let className =
  Css.(
    merge([
      "my-5 md:my-16",
      style([
        display(`grid),
        gridTemplateColumns([`px(20), `fr(1.0), `px(20)]),
        selector("> *", [gridColumn(2, 2)]),
        media(
          "(min-width: 768px)",
          [gridTemplateColumns([`fr(1.0), `px(600), `fr(1.0)])],
        ),
      ]),
    ])
  );

[@react.component]
let make = (~children) => {
  <div className> children </div>;
};
