type state = {blocks: list(WorkoutBlock.t)};

type action =
  | AddBlock
  | DuplicateBlock(WorkoutBlock.t);

module GetExercises = [%graphql
  {|
	query allExercises {
		allExercises(orderBy: NAME_ASC) {
			nodes {
        id
				name
				equipment
			}
		}
	}
|}
];

module GetExercisesQuery = ReasonApollo.CreateQuery(GetExercises);

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | AddBlock => {
            blocks:
              state.blocks
              ->Belt.List.add({
                  id: Js.Date.now(),
                  equipment: 0,
                  reps: 0,
                  weight: 0.0,
                }),
          }
        | DuplicateBlock(block) => {
            blocks:
              state.blocks->Belt.List.add({...block, id: Js.Date.now()}),
          }
        },
      {blocks: [{id: Js.Date.now(), equipment: 0, reps: 0, weight: 0.0}]},
    );

  <GetExercisesQuery>
    ...{({result}) =>
      switch (result) {
      | Loading => <div> "Loading"->React.string </div>
      | Error(error) => <div> {error##message->React.string} </div>
      | Data(response) =>
        let exercises = [%get_in
          response##allExercises#?nodes
          ->Belt.Option.getWithDefault([||])
          ->Belt.Array.keepMap(node => node)
        ];

        <>
          {state.blocks
           ->Belt.List.reverse
           ->Belt.List.map(block =>
               <WorkoutBlock
                 block
                 duplicateBlock={db => dispatch(DuplicateBlock(db))}
                 exercises
                 key={block.id->Js.Float.toString}
               />
             )
           ->Belt.List.toArray
           ->React.array}
          <button onClick={_ => dispatch(AddBlock)}>
            "Add block"->React.string
          </button>
        </>;
      }
    }
  </GetExercisesQuery>;
};
