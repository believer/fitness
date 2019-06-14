module GetAllWODs = [%graphql
  {|
    query allWods {
      allWods {
        id
        createdAt
        name
        totalWeight
        exercises {
          id
          exercise {
            name
          }
        }
      }
    }
 |}
];

module GetAllWODsQuery = ReasonApollo.CreateQuery(GetAllWODs);

[@react.component]
let make = () => {
  <Wrapper>
    <GetAllWODsQuery>
      {({result}) =>
         switch (result) {
         | Loading => <div> "Loading"->React.string </div>
         | Error(error) => <div> {error##message->React.string} </div>
         | Data(response) =>
           let wods =
             response##allWods
             ->Belt.List.fromArray
             ->Belt.List.map(Workout.make);
           let totalWeight =
             wods->Belt.List.reduce(0.0, (a, b) => a +. b.totalWeight);

           <div>
             <div className="flex border-b border-gray-400">
               <div className="w-1/2 p-3 border-r border-gray-400">
                 <div className="text-2xl">
                   {wods->Belt.List.length->string_of_int->React.string}
                 </div>
                 <div className="text-gray-500 mt-1 text-sm">
                   "workouts completed"->React.string
                 </div>
               </div>
               <div className="w-1/2 p-3">
                 <div className="text-2xl">
                   {switch (totalWeight) {
                    | w when w > 1000.0 =>
                      (w /. 1000.0)->Js.Float.toString->React.string
                    | w => w->Js.Float.toString->React.string
                    }}
                 </div>
                 <div className="text-gray-500 mt-1 text-sm">
                   {switch (totalWeight) {
                    | w when w > 1000.0 =>
                      <div> "tons lifted"->React.string </div>
                    | _ => <div> "kgs lifted"->React.string </div>
                    }}
                 </div>
               </div>
             </div>
             {switch (wods) {
              | [first, ..._tail] => <LatestWorkout workout=first />
              | [] => React.null
              }}
             {switch (wods) {
              | [_first, ...wods] =>
                wods
                ->Belt.List.map(({id, createdAt, name, numberOfExercises}) =>
                    <Router.Link
                      className="flex items-center p-3 border-b border-gray-400"
                      href={"/workout/" ++ id}
                      key=id>
                      <DateTime date=createdAt />
                      <div className="ml-3">
                        <Typography.H3 className="font-semibold mt-0 mb-1">
                          name->React.string
                        </Typography.H3>
                        <div className="text-sm text-gray-500">
                          {switch (numberOfExercises) {
                           | 0 => React.null
                           | 1 => "1 exercise completed"->React.string
                           | v =>
                             v->string_of_int
                             ++ " exercises completed"
                             |> React.string
                           }}
                        </div>
                      </div>
                    </Router.Link>
                  )
                ->Belt.List.toArray
                ->React.array
              | [] => React.null
              }}
           </div>;
         }}
    </GetAllWODsQuery>
  </Wrapper>;
};
