[@react.component]
let make = (~date) => {
  <div className="bg-blue-400 text-white p-3 rounded text-center">
    <div className="text-xl font-semibold">
      {date |> DateFns.format("DD") |> React.string}
    </div>
    <div className="text-sm font-light uppercase">
      {date |> DateFns.format("MMM") |> React.string}
    </div>
  </div>;
};
