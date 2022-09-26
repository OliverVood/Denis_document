<?php

	namespace Base\DB;

	use Base\DB;

	class FieldEnumMySQLi extends DB\FieldMySQLi {
		private array $enum;

		public function __construct(string $name, array $enum) {
			parent::__construct('enum', $name);

			$this->enum = $enum;
		}

		public function Check(?array $old) { echo "Check field $this->type<br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}