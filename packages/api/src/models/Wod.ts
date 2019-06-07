import { db } from '../adapters/db'
import { Model } from 'objection'
import WodExercise from './WodExercise'

Model.knex(db)

export default class Wod extends Model {
  exercises!: WodExercise[]
  updatedAt!: string

  static tableName = 'wod'

  static relationMappings = {
    exercises: {
      relation: Model.HasManyRelation,
      modelClass: WodExercise,
      join: {
        from: 'wod.id',
        to: 'wod_exercise.wodId',
      },
    },
  }

  $beforeUpdate() {
    this.updatedAt = new Date().toISOString()
  }
}
