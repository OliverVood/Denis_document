<?php

	namespace Base\DB;

	use Base\DB;

	class FieldTimestamp extends DB\Field {
		private bool $update;

		public function __construct(string $name, bool $update) {
			parent::__construct('timestamp', $name);

			$this->update = $update;
		}

	}