[@react.component]
let make = (~date) => {
  let formattedDate = date |> Js.Float.fromString |> Js.Date.fromFloat;

  <div className="bg-blue-400 text-white p-4 rounded text-center">
    <div className="text-xl font-semibold">
      {formattedDate |> DateFns.format("DD") |> React.string}
    </div>
    <div className="text-sm font-light uppercase">
      {formattedDate |> DateFns.format("MMM") |> React.string}
    </div>
  </div>;
};
