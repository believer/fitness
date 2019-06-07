import { DB } from '../adapters/db'
import Exercise from './Exercise'

export default class WodExercise extends DB {
  static tableName = 'wod_exercise'

  static relationMappings = {
    exercise: {
      relation: DB.HasOneRelation,
      modelClass: Exercise,
      join: {
        from: 'wod_exercise.exerciseId',
        to: 'exercise.id',
      },
    },
  }
}
