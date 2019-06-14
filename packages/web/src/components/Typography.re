module H1 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h1 className={Cn.make(["text-2xl", className->Cn.unpack])}>
      children
    </h1>;
  };
};

module H2 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h2 className={Cn.make(["text-xl", className->Cn.unpack])}>
      children
    </h2>;
  };
};

module H3 = {
  [@react.component]
  let make = (~children, ~className=?) => {
    <h3 className={Cn.make(["text-lg", className->Cn.unpack])}>
      children
    </h3>;
  };
};
