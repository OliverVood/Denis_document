<?php

	namespace Base\DB;

	use Base\DB;

	class FieldTimestampMySQLi extends DB\FieldMySQLi {
		private bool $update;

		public function __construct(string $name, bool $update) {
			parent::__construct('timestamp', $name);

			$this->update = $update;
		}

		public function Check(?array $old) { echo "Check field $this->type<br>"; }
		public function Make() { echo "Make field $this->type<br>"; }

	}