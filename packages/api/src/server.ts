import express from 'express'
import { ApolloServer, gql } from 'apollo-server-express'
import {
  resolvers as exerciseResolvers,
  typeDef as Exercise,
} from './resolvers/queries/exercises'
import {
  resolvers as wodResolvers,
  typeDef as Wod,
} from './resolvers/queries/wods'
import merge from 'lodash.merge'

const Query = gql`
  type Query {
    _empty: String
  }
`

const server = new ApolloServer({
  typeDefs: [Query, Wod, Exercise],
  resolvers: merge(wodResolvers, exerciseResolvers),
})

const app = express()
server.applyMiddleware({ app })

app.listen({ port: 4000 }, () =>
  console.log(`🚀 Server ready at http://localhost:4000${server.graphqlPath}`)
)
