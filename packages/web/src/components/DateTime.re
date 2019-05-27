[@react.component]
let make = (~date) => {
  <div>
    {switch (Js.Json.decodeString(date)) {
     | Some(validDate) =>
       validDate
       |> Js.Date.fromString
       |> DateFns.format("YYYY-MM-DD")
       |> React.string
     | None => {j|Ogiltigt datum|j}->React.string
     }}
  </div>;
};
