<?php

	namespace Base\DB;

	use Base\DB;

	class FieldBool extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('bool', $name);
		}

	}