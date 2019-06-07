import Wod from '../../models/Wod'
import { gql } from 'apollo-server-express'

export const typeDef = gql`
  enum ExerciseAssistance {
    BandGray
  }

  enum ExerciseEquipment {
    Barbell
    Bodyweight
    BulgarianBag
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

  type WodExercise {
    id: ID!
    reps: Int!
    weight: Float
    exercise: Exercise!
  }

  type WOD {
    id: ID!
    createdAt: String!
    updatedAt: String!
    name: String
    exercises: [WodExercise!]!
  }

  extend type Query {
    wodById(id: ID!): WOD
    allWods: [WOD!]!
  }
`

export const resolvers = {
  Query: {
    wodById: (_: any, { id }: { id: string }) =>
      Wod.query()
        .findById(id)
        .eager('[exercises.[exercise]]'),
    allWods: () => Wod.query().eager('[exercises.[exercise]]'),
  },
}
