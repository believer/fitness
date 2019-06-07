require('dotenv').config()

import { knexSnakeCaseMappers } from 'objection'
import Knex from 'knex'
import pg from 'pg'

pg.defaults.ssl = true

export const db = Knex({
  client: 'pg',
  useNullAsDefault: true,
  connection: process.env.DATABASE_URL,
  ...knexSnakeCaseMappers(),
})
