-- DOWN
DROP SCHEMA IF EXISTS public CASCADE;

-- UP
CREATE SCHEMA public;

GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO public;

-- Equipment enum
CREATE TYPE exercise_equipment as enum (
  'Barbell',
  'Dumbbell',
  'Kettlebell',
  'Rower',
  'SkiErg',
  'Bodyweight',
  'BulgarianBag'
);

CREATE TYPE exercise_assistance as enum (
  'BandGray'
);

CREATE TABLE wod (
  id          serial primary key,
  name        text,
  created_at  timestamp not null DEFAULT NOW(),
  updated_at  timestamp not null DEFAULT NOW()
);

-- Exercise table
CREATE TABLE exercise (
  id          serial primary key,
  name        text not null,
  equipment   exercise_equipment not null,
  assistance  exercise_assistance,
  UNIQUE (name, equipment)
);

-- Sets table
CREATE TABLE wod_exercise (
  id           serial primary key,
  exercise_id  int not null references exercise(id),
  wod_id       int not null references wod(id) ON DELETE CASCADE,
  reps         int not null,
  weight       float
);

COMMENT ON TABLE public.wod_exercise IS 'A set of an exercise in a WOD';

CREATE OR REPLACE FUNCTION public.wod_total_weight (wod public.wod) RETURNS float AS $$
  SELECT
    SUM(COALESCE(we.weight, 0) * COALESCE(we.reps, 0))
  FROM wod_exercise AS we 
  WHERE we.wod_id = wod.id;
$$ language sql stable;

COMMENT ON FUNCTION public.wod_total_weight(public.wod)
IS 'The total weight for all exercises in the WOD';

-- INSERT DATA
INSERT INTO exercise (name, equipment, assistance) VALUES
  ('Hang Power Clean', 'Barbell', NULL),
  ('Deadlift', 'Barbell', NULL),
  ('Sumo deadlift high pull', 'Barbell', NULL),
  ('Push press', 'Barbell', NULL),
  ('Thruster', 'Barbell', NULL),
  ('Burpee over bar', 'Bodyweight', NULL),
  ('Power Clean', 'Barbell', NULL),
  ('SkiErg', 'SkiErg', NULL),
  ('Row', 'Rower', NULL),
  ('Hang Power Snatch', 'Dumbbell', NULL),
  ('One Side Bulgarian Bag Squat', 'BulgarianBag', NULL),
  ('Russian Kettlebell Swing', 'Kettlebell', NULL),
  ('Squat Snatch', 'Barbell', NULL),
  ('Back squat', 'Barbell', NULL),
  ('Bench press', 'Barbell', NULL),
  ('Pull-up', 'Bodyweight', 'BandGray'),
  ('Deadlift', 'Kettlebell', NULL),
  ('Box jump 50 cm', 'Bodyweight', NULL),
  ('Bicep Curl', 'Dumbbell', NULL),
  ('Hang High Pull', 'Barbell', NULL),
  ('Jerk Dip Squat', 'Barbell', NULL),
  ('Split Jerk', 'Barbell', NULL),
  ('Goblet Squat', 'Kettlebell', NULL),
  ('One-arm Kettlebell Swing', 'Kettlebell', NULL),
  ('Push Jerk', 'Barbell', NULL)
ON CONFLICT DO NOTHING;

INSERT INTO wod (name, created_at) VALUES (NULL, '2019-05-23 06:00');
INSERT INTO wod (name, created_at) VALUES ('Chip through Monday', '2019-05-24 06:00');
INSERT INTO wod (name, created_at) VALUES (NULL, '2019-05-25 07:15');
INSERT INTO wod (name, created_at) VALUES (NULL, '2019-05-28 06:00');
INSERT INTO wod (name, created_at) VALUES ('DT', '2019-05-29 06:00');
INSERT INTO wod (name, created_at) VALUES (NULL, '2019-05-29 06:30');

INSERT INTO wod_exercise (exercise_id, wod_id, reps, weight) VALUES
  (13, 1, 3, 30),
  (13, 1, 3, 40),
  (13, 1, 3, 42.5),
  (13, 1, 3, 45),
  (13, 1, 3, 47.5),
  (8, 1, 10, NULL),
  (9, 1, 20, NULL),
  (10, 1, 30, 17.5),
  (11, 1, 40, 10),
  (12, 1, 50, 24);

INSERT INTO wod_exercise (exercise_id, wod_id, reps, weight) VALUES
  (6, 2, 5, NULL),
  (5, 2, 10, 40),
  (6, 2, 5, NULL),
  (3, 2, 15, 40),
  (6, 2, 5, NULL),
  (4, 2, 20, 40),
  (6, 2, 5, NULL),
  (1, 2, 25, 40),
  (6, 2, 5, NULL),
  (2, 2, 30, 60),
  (6, 2, 5, NULL);

INSERT INTO wod_exercise (exercise_id, wod_id, reps, weight) VALUES
  (14, 3, 8, 40),
  (14, 3, 8, 50),
  (14, 3, 8, 60),
  (14, 3, 8, 70),
  (14, 3, 8, 80),
  (15, 3, 10, 20),
  (15, 3, 10, 40),
  (15, 3, 10, 45),
  (15, 3, 10, 50),
  (16, 3, 5, NULL),
  (16, 3, 4, NULL),
  (16, 3, 3, NULL),
  -- WOD 4 rounds
  (8, 3, 9, NULL),
  (17, 3, 7, 32),
  (18, 3, 5, NULL),
  (19, 3, 5, 12.5),
  (8, 3, 9, NULL),
  (17, 3, 7, 32),
  (18, 3, 5, NULL),
  (19, 3, 5, 12.5),
  (8, 3, 9, NULL),
  (17, 3, 7, 32),
  (18, 3, 5, NULL),
  (19, 3, 5, 12.5),
  (8, 3, 9, NULL),
  (17, 3, 7, 32),
  (18, 3, 5, NULL),
  (19, 3, 5, 12.5);
  
INSERT INTO wod_exercise (exercise_id, wod_id, reps, weight) VALUES
  (20, 4, 1, 40),
  (1, 4, 1, 40),
  (21, 4, 1, 40),
  (22, 4, 1, 40),
  (20, 4, 1, 50),
  (1, 4, 1, 50),
  (21, 4, 1, 50),
  (22, 4, 1, 50),
  (20, 4, 1, 55),
  (1, 4, 1, 55),
  (21, 4, 1, 55),
  (22, 4, 1, 55),
  (20, 4, 1, 57.5),
  (1, 4, 1, 57.5),
  (21, 4, 1, 57.5),
  (22, 4, 1, 57.5),
  (20, 4, 1, 60),
  (1, 4, 1, 60),
  (21, 4, 1, 60),
  (22, 4, 1, 60),
  (20, 4, 1, 62.5),
  (1, 4, 1, 62.5),
  (21, 4, 1, 62.5),
  (22, 4, 1, 62.5),
  -- WOD 11-9-7-5
  (9, 4, 11, NULL),
  (23, 4, 11, 24),
  (24, 4, 11, 16),
  (9, 4, 9, NULL),
  (23, 4, 9, 24),
  (24, 4, 9, 16),
  (9, 4, 7, NULL),
  (23, 4, 7, 24),
  (24, 4, 7, 16),
  (9, 4, 5, NULL),
  (23, 4, 5, 24),
  (24, 4, 5, 16);
  
INSERT INTO wod_exercise (exercise_id, wod_id, reps, weight) VALUES
  (2, 5, 12, 50),
  (1, 5, 9, 50),
  (25, 5, 6, 50),
  (2, 5, 12, 50),
  (1, 5, 9, 50),
  (25, 5, 6, 50),
  (2, 5, 12, 50),
  (1, 5, 9, 50),
  (25, 5, 6, 50),
  (2, 5, 12, 50),
  (1, 5, 9, 50),
  (25, 5, 6, 50),
  (2, 5, 12, 50),
  (1, 5, 9, 50),
  (25, 5, 6, 50);
  
INSERT INTO wod_exercise (exercise_id, wod_id, reps, weight) VALUES
  (19, 6, 12, 12.5),
  (19, 6, 10, 12.5),
  (19, 6, 10, 12.5);
  
INSERT INTO wod (name, created_at) VALUES (NULL, '2019-05-31 12:00');

INSERT INTO wod_exercise (exercise_id, wod_id, reps, weight) VALUES
  (7, 7, 1, 40),
  (1, 7, 1, 40),
  (32, 7, 1, 40),
  (7, 7, 1, 40),
  (1, 7, 1, 40),
  (32, 7, 1, 40),
  (7, 7, 1, 45),
  (1, 7, 1, 45),
  (32, 7, 1, 45),
  (7, 7, 1, 47.5),
  (1, 7, 1, 47.5),
  (32, 7, 1, 47.5),
  
  -- SC
  (33, 7, 2, 47.5),
  (33, 7, 2, 50),
  (33, 7, 2, 52.5),
  
  -- OHS
  (34, 7, 3, 52.5),
  (34, 7, 3, 52.5),
  (34, 7, 3, 52.5),
  
  (9, 7, 10, NULL),
  (35, 7, 5, 30),
  (8, 7, 8, NULL),
  (36, 7, 10, 15),
  (9, 7, 10, NULL),
  (35, 7, 5, 30),
  (8, 7, 8, NULL),
  (36, 7, 10, 15),
  (9, 7, 10, NULL),
  (35, 7, 5, 30),
  (8, 7, 8, NULL),
  (36, 7, 10, 15),
  (9, 7, 10, NULL),
  (35, 7, 5, 30),
  (8, 7, 8, NULL),
  (36, 7, 10, 15);
  
  INSERT INTO wod (name, created_at) VALUES (NULL, '2019-06-08 12:00');

INSERT INTO wod_exercise (exercise_id, wod_id, reps, weight) VALUES
  -- SS
  (13, 8, 2, 40),
  (13, 8, 2, 45),
  (13, 8, 1, 47.5),
  (13, 8, 2, 47.5),
  (13, 8, 2, 50),
  (13, 8, 1, 52.5),
  (13, 8, 2, 55),
  
  -- FS
  (26, 8, 5, 50),
  (26, 8, 5, 60),
  (26, 8, 5, 65),
  (26, 8, 3, 70),
  (26, 8, 3, 72.5),
  
  -- 3 RFT
  (8, 8, 10, NULL),
  (29, 8, 10, 15),
  (27, 8, 8, 40),
  (28, 8, 5, NULL),
  (8, 8, 10, NULL),
  (29, 8, 10, 15),
  (27, 8, 8, 40),
  (28, 8, 5, NULL),
  (8, 8, 10, NULL),
  (29, 8, 10, 15),
  (27, 8, 8, 40),
  (28, 8, 5, NULL),
  
  -- IBP
  (30, 8, 8, 17.5),
  (31, 8, 12, 12),
  (30, 8, 8, 17.5),
  (31, 8, 8, 12),
  (30, 8, 8, 17.5),
  (31, 8, 8, 12);