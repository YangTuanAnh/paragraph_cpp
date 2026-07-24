-- CREATE TABLE IF NOT EXISTS "tasks" (
--   "id" uuid PRIMARY KEY DEFAULT (uuid_generate_v4()),
--   "text" text NOT NULL,
--   "user_id" uuid,
--   "project_id" uuid,
--   "done" boolean DEFAULT false,
--   "inbox" boolean DEFAULT true,
--   "archived" boolean DEFAULT false,
--   "urgency" "Urgency",
--   "energy" "Energy",
--   "created_at" timestamp DEFAULT (now()),
--   "updated_at" timestamp DEFAULT (now()),
--   "archived_at" timestamp,
--   "deleted_at" timestamp
-- );

CREATE TABLE IF NOT EXISTS "areas" (
  "id" uuid PRIMARY KEY NOT NULL,
  "text" text DEFAULT '',
  "category" varchar DEFAULT '',
  "user_id" uuid,
  "done" boolean DEFAULT false,
  "archived" boolean DEFAULT false,
  "created_at" timestamp DEFAULT CURRENT_TIMESTAMP,
  "updated_at" timestamp DEFAULT CURRENT_TIMESTAMP,
  "start_at" timestamp,
  "due_at" timestamp
);

CREATE TABLE IF NOT EXISTS "projects" (
  "id" uuid PRIMARY KEY NOT NULL,
  "text" text DEFAULT '',
  "area_id" uuid DEFAULT '',
  "user_id" uuid,
  "done" boolean DEFAULT false,
  "archived" boolean DEFAULT false,
  "created_at" timestamp DEFAULT CURRENT_TIMESTAMP,
  "updated_at" timestamp DEFAULT CURRENT_TIMESTAMP,
  "start_at" timestamp,
  "due_at" timestamp
);


CREATE TABLE IF NOT EXISTS "tasks" (
  "id" uuid PRIMARY KEY NOT NULL,
  "text" text DEFAULT '',
  "project_id" uuid DEFAULT '',
  "user_id" uuid,
  "done" boolean DEFAULT false,
  "inbox" boolean DEFAULT false,
  "archived" boolean DEFAULT false,
  "urgency" INTEGER CHECK (urgency >= 0 AND urgency <= 4) DEFAULT 0,  
  "energy" INTEGER CHECK (energy >= 0 AND energy <= 7) DEFAULT 0,  
  "created_at" timestamp DEFAULT CURRENT_TIMESTAMP,
  "updated_at" timestamp DEFAULT CURRENT_TIMESTAMP,
  "start_at" timestamp,
  "due_at" timestamp
);

CREATE TABLE IF NOT EXISTS "resources" (
  "id" uuid PRIMARY KEY NOT NULL,
  "text" text DEFAULT '',
  "area_id" uuid DEFAULT '',
  "source" text DEFAULT '',
  "user_id" uuid,
  "archived" boolean DEFAULT false,
  "resource_type" INTEGER CHECK (resource_type >= 0 AND resource_type <= 8) DEFAULT 0,  
  "created_at" timestamp DEFAULT CURRENT_TIMESTAMP,
  "updated_at" timestamp DEFAULT CURRENT_TIMESTAMP
);