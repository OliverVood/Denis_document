<?php

	namespace Base\DB;

	use Base\DB;

	class FieldTextMySQLi extends DB\FieldMySQLi {
		public function __construct(string $name) {
			parent::__construct('text', $name);
		}

		public function Check(?array $old) { echo "Check field $this->type<br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}