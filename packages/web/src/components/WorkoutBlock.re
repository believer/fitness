type t = {
  id: float,
  equipment: int,
  reps: int,
  weight: float,
};

type state = t;

type action =
  | UpdateEquipment(int)
  | UpdateReps(int)
  | UpdateWeight(float);

let equipmentType =
  fun
  | `Dumbbell => "(DB)"
  | `Kettlebell => "(KB)"
  | _ => "";

[@react.component]
let make = (~block, ~duplicateBlock, ~exercises) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | UpdateEquipment(equipment) => {...state, equipment}
        | UpdateReps(reps) => {...state, reps}
        | UpdateWeight(weight) => {...state, weight}
        },
      block,
    );

  <div>
    <select
      id=""
      name=""
      onChange={e =>
        dispatch(
          UpdateEquipment(e->ReactEvent.Form.target##value->int_of_string),
        )
      }
      value={state.equipment->string_of_int}>
      <option value="select"> "Select exercise"->React.string </option>
      {exercises
       ->Belt.Array.map(exercise =>
           <option key={exercise##id} value={exercise##id}>
             {exercise##name
              ++ " "
              ++ exercise##equipment->equipmentType
              |> React.string}
           </option>
         )
       ->React.array}
    </select>
    <input
      onChange={e =>
        dispatch(UpdateReps(e->ReactEvent.Form.target##value->int_of_string))
      }
      placeholder="Reps"
      type_="text"
      value={state.reps->string_of_int}
    />
    <input
      onChange={e =>
        dispatch(
          UpdateWeight(e->ReactEvent.Form.target##value->Js.Float.fromString),
        )
      }
      placeholder="Weight"
      type_="text"
      value={state.weight->Js.Float.toString}
    />
    <button onClick={_ => duplicateBlock(state)}>
      "Duplicate"->React.string
    </button>
  </div>;
};
