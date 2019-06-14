[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <div>
    {switch (url.path) {
     | [] => <Workouts />
     | ["workout", "add"] => <AddWorkout />
     | ["workout", id] => <Workout id />
     | ["exercise", id] => <WorkoutExercise id />
     | _ => <div> "Not found"->React.string </div>
     }}
  </div>;
};
