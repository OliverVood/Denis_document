<?php

	namespace Base\DB;

	use Base\DB;

	class FieldDouble extends DB\Field {
		public function __construct(string $name) {
			parent::__construct('double', $name);
		}

	}