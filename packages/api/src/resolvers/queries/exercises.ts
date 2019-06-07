import { gql } from 'apollo-server-express'
import Exercise from '../../models/Exercise'

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

  extend type Query {
    allExercises: [Exercise!]!
  }
`

export const resolvers = {
  Query: {
    allExercises: async () => {
      const wods = await Exercise.query()

      return wods
    },
  },
}
