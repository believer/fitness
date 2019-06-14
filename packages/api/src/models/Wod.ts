import { db } from '../adapters/db'
import { Model } from 'objection'
import path from 'path'

Model.knex(db)

export default class Wod extends Model {
  exercises!: any[]
  updatedAt!: string

  static tableName = 'wod'

  static get relationMappings() {
    return {
      exercises: {
        relation: Model.HasManyRelation,
        modelClass: path.join(__dirname, 'WodExercise'),
        join: {
          from: 'wod.id',
          to: 'wod_exercise.wodId',
        },
      },
    }
  }

  $beforeUpdate() {
    this.updatedAt = new Date().toISOString()
  }
}
