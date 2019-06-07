import express from 'express'
import { ApolloServer, gql } from 'apollo-server-express'
import {
  resolvers as wodResolvers,
  typeDef as WODS,
} from './resolvers/queries/wods'
import merge from 'lodash.merge'

const Query = gql`
  type Query {
    _empty: String
  }
`

const server = new ApolloServer({
  typeDefs: [Query, WODS],
  resolvers: merge(wodResolvers),
})

const app = express()
server.applyMiddleware({ app })

app.listen({ port: 4000 }, () =>
  console.log(`🚀 Server ready at http://localhost:4000${server.graphqlPath}`)
)
