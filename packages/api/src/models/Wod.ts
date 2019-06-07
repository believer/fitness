import { DB } from '../adapters/db'
import WodExercise from './WodExercise'

export default class Wod extends DB {
  static tableName = 'wod'

  static relationMappings = {
    exercises: {
      relation: DB.HasManyRelation,
      modelClass: WodExercise,
      join: {
        from: 'wod.id',
        to: 'wod_exercise.wodId',
      },
    },
  }
}
