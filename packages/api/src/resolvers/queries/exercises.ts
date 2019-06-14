import { gql } from 'apollo-server-express'
import Exercise from '../../models/Exercise'
import WodExercise from '../../models/WodExercise'

export const typeDef = gql`
  enum ExerciseAssistance {
    BandGray
  }

  enum ExerciseEquipment {
    Barbell
    Bodyweight
    BulgarianBag
    Curlbar
    Dumbbell
    Kettlebell
    Rower
    SkiErg
  }

  type Exercise {
    id: ID!
    equipment: ExerciseEquipment!
    assistance: ExerciseAssistance
    name: String!
  }

  type ExerciseByWod {
    id: ID!
    exerciseId: ID!
    equipment: ExerciseEquipment!
    assistance: ExerciseAssistance
    name: String!
    reps: Int!
    weight: Float
    wodName: String
    createdAt: String!
  }

  extend type Query {
    allExercises: [Exercise!]!
    allWodsWithExercise(exerciseId: ID!): [ExerciseByWod!]!
  }
`

export const resolvers = {
  Query: {
    allExercises: () => Exercise.query(),

    allWodsWithExercise: async (_: any, { exerciseId }: any) =>
      WodExercise.query()
        .alias('we')
        .select(
          'we.id',
          'we.reps',
          'we.weight',
          'e.id as exercise_id',
          'e.name',
          'e.equipment',
          'e.assistance',
          'w.name as wod_name',
          'w.created_at'
        )
        .rightJoinRelation('[exercise as e, wod as w]')
        .where({
          exerciseId,
        }),
  },
}
