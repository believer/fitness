open Css;

global("*", [boxSizing(`borderBox)]);

global(
  "html, body",
  [
    backgroundColor(Theme.Colors.athensGray),
    color(Theme.Colors.balticSea),
    fontFamily(Theme.Typography.fontStack),
    fontSize(Theme.Typography.fontSize(`Small)),
    fontWeight(`normal),
    margin(`zero),
    padding(`zero),
  ],
);

global("a", [color(Theme.Colors.balticSea), textDecoration(`none)]);
