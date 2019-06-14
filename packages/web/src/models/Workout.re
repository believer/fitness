type t = {
  createdAt: Js.Date.t,
  id: string,
  name: string,
  numberOfExercises: int,
  totalWeight: float,
};

let make = workout => {
  createdAt: workout##createdAt |> Js.Float.fromString |> Js.Date.fromFloat,
  id: workout##id,
  name:
    switch (workout##name) {
    | Some(name) => name
    | None =>
      workout##exercises
      ->Belt.Array.slice(~offset=0, ~len=3)
      ->Belt.Array.map(exercise => exercise##exercise##name)
      |> Js.Array.joinWith(", ")
    },
  numberOfExercises: workout##exercises->Belt.Array.length,
  totalWeight: workout##totalWeight->Belt.Option.getWithDefault(0.0),
};
