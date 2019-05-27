module Style = {
  open Css;

  let heading = style([marginBottom(`zero), marginTop(`zero)]);

  let h1 =
    merge([
      heading,
      style([fontSize(Theme.Typography.fontSize(`Heading1))]),
    ]);

  let h2 =
    merge([
      heading,
      style([fontSize(Theme.Typography.fontSize(`Heading2))]),
    ]);

  let h3 =
    merge([
      heading,
      style([fontSize(Theme.Typography.fontSize(`Heading3))]),
    ]);
};

module H1 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h1 className={Cn.make([Style.h1, className->Cn.unpack])}> children </h1>;
  };
};

module H2 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h2 className={Cn.make([Style.h2, className->Cn.unpack])}> children </h2>;
  };
};

module H3 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h3 className={Cn.make([Style.h3, className->Cn.unpack])}> children </h3>;
  };
};
