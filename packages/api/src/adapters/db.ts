require('dotenv').config()

import { Model, knexSnakeCaseMappers } from 'objection'
import Knex from 'knex'
import pg from 'pg'

pg.defaults.ssl = true

const knex = Knex({
  client: 'pg',
  useNullAsDefault: true,
  connection: process.env.DATABASE_URL,
  ...knexSnakeCaseMappers(),
})

Model.knex(knex)

export const DB = Model
