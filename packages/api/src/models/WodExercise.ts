import { db } from '../adapters/db'
import { Model } from 'objection'
import path from 'path'

Model.knex(db)

export default class WodExercise extends Model {
  reps!: number
  weight!: number

  static tableName = 'wod_exercise'

  static get relationMappings() {
    return {
      exercise: {
        relation: Model.HasOneRelation,
        modelClass: path.join(__dirname, 'Exercise'),
        join: {
          from: 'wod_exercise.exerciseId',
          to: 'exercise.id',
        },
      },
      wod: {
        relation: Model.HasManyRelation,
        modelClass: path.join(__dirname, 'Wod'),
        join: {
          from: 'wod_exercise.wodId',
          to: 'wod.id',
        },
      },
    }
  }
}
