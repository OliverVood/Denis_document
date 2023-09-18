<?php

	namespace Base\DB\MySQLi;

	class Foreign extends Key {
		private string $references_table;
		private array $references_fields;
		private int $relationship_from;
		private int $relationship_to;

		public function __construct(string $name, Table $table, array $fields, string $references_table, array $references_fields, int $relationship_from = \Base\DB\DBObject::ER_RELATIONSHIP_ONE, int $relationship_to = \Base\DB\DBObject::ER_RELATIONSHIP_MANY) {
			parent::__construct('foreign', $name, $table, $fields);

			$this->references_table = $references_table;
			$this->references_fields = $references_fields;
			$this->relationship_from = $relationship_from;
			$this->relationship_to = $relationship_to;
		}

		public function Create(): void {  }

		public function Structure(): array {
			return [
				'type' => $this->type,
				'name' => $this->name,
				'fields' => $this->fields,
				'references_table' => $this->references_table,
				'references_fields' => $this->references_fields,
				'relationship_from' => $this->relationship_from,
				'relationship_to' => $this->relationship_to,
			];
		}

	}