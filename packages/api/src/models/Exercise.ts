import { db } from '../adapters/db'
import { Model } from 'objection'

Model.knex(db)

export default class Exercise extends Model {
  static tableName = 'exercise'
}
