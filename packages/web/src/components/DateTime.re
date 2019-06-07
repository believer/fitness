[@react.component]
let make = (~date) => {
  <div>
    {date
     |> Js.Float.fromString
     |> Js.Date.fromFloat
     |> DateFns.format("YYYY-MM-DD")
     |> React.string}
  </div>;
};
