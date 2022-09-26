<?php

	namespace Base\DB;

	use Base\DB;

	class FieldStringMySQLi extends DB\FieldMySQLi {
		private int $length;

		public function __construct(string $name, int $length) {
			parent::__construct('enum', $name);

			$this->length = $length;
		}

		public function Check(?array $old) { echo "Check field $this->type<br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}