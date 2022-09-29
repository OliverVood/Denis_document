<?php

	namespace Base\DB;

	use Base\DB;

	class FieldTimestampMySQLi extends DB\FieldMySQLi {
		private bool $update;

		public function __construct(string $name, bool $update, TableMySQLi $table) {
			parent::__construct('timestamp', $name, $table);

			$this->update = $update;
		}

		public function Check(?array $old) { echo "Проверка поля <b>`{$this->name}`</b><br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}