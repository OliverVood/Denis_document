<?php

	namespace Base\DB;

	use Base\DB;

	class FieldSetMySQLi extends DB\FieldMySQLi {
		private array $set;

		public function __construct(string $name, array $set) {
			parent::__construct('set', $name);

			$this->set = $set;
		}

		public function Check(?array $old) { echo "Check field $this->type<br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}