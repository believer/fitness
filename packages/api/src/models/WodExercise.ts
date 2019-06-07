import Exercise from './Exercise'
import { db } from '../adapters/db'
import { Model } from 'objection'

Model.knex(db)

export default class WodExercise extends Model {
  reps!: number
  weight!: number

  static tableName = 'wod_exercise'

  static relationMappings = {
    exercise: {
      relation: Model.HasOneRelation,
      modelClass: Exercise,
      join: {
        from: 'wod_exercise.exerciseId',
        to: 'exercise.id',
      },
    },
  }
}
