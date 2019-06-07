import Wod from '../../models/Wod'
import { gql } from 'apollo-server-express'
import WodExercise from '../../models/WodExercise'

export const typeDef = gql`
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
    totalWeight: Float
  }

  extend type Query {
    wodById(id: ID!): WOD
    allWods: [WOD!]!
  }
`

const calculateTotalWeight = (exercises: WodExercise[]) =>
  exercises.reduce((acc, curr) => acc + curr.weight * curr.reps, 0)

export const resolvers = {
  Query: {
    wodById: async (_: any, { id }: { id: string }) => {
      const wod = await Wod.query()
        .findById(id)
        .eager('[exercises.[exercise]]')

      if (!wod) {
        return null
      }

      return {
        ...wod,
        totalWeight: calculateTotalWeight(wod.exercises),
      }
    },

    allWods: async () => {
      const wods = await Wod.query()
        .eager('[exercises.[exercise]]')
        .orderBy('createdAt', 'desc')

      return wods.map(wod => ({
        ...wod,
        totalWeight: calculateTotalWeight(wod.exercises),
      }))
    },
  },
}
