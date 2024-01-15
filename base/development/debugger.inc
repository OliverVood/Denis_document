<?php

	namespace Base;

	use Base\DB\DBQuery;
	use Proj\Admin\Model\Users;
	use ReflectionClass;
	use ReflectionClassConstant;
	use ReflectionMethod;
	use ReflectionProperty;

	abstract class Debugger {
		private static array $vars = [];
		private static ?DBQuery $db = null;

		public static function SetDB($db): void {
			self::$db = $db;
		}

		public static function Get(): array {
			return [
				'network' => [
					'area' => Controller::$area,
					'part' => Controller::$part,
					'point' => ENTRY,
					'type' => ROUTE,
					'href' => ADDRESS . $_SERVER['REQUEST_URI'],
					'ip' => GetUserIP()
				],
				'post' => [['title' => '', 'var' => self::ParsingVar($_POST)]],
				'get' => [['title' => '', 'var' => self::ParsingVar($_GET)]],
				'files' => [['title' => '', 'var' => self::ParsingVar($_FILES)]],
				'variables' => self::$vars,
				'queries' => self::$db->GetQueryList(),
				'controllers' => Unit::GetUnitList(),
				'models' => Model::GetModelList(),
				'timestamps' => Timestamp::GetTimestampList(),
				'user' => [
					'name' => Users::instance()->GetAlias()
				]
			];
		}

		public static function Var(mixed $var, string $title = ''): void {
			self::$vars[] = ['title' => $title, 'var' => self::ParsingVar($var)];
		}

		private static function ParsingVar(mixed $var): array {
			$type = gettype($var);
			return match ($type) {
				'integer', 'double', 'string' => ['type' => $type, 'value' => $var],
				'NULL' => ['type' => 'null', 'value' => $var],
				'array' => ['type' => $type, 'value' => self::ParsingArray($var)],
				'object' => ['type' => $type, 'value' => self::ParsingObject($var)],
				default => ['type' => $type],
			};
		}

		private static function ParsingArray(array $array): array {
			$out = [];
			foreach ($array as $key => $value) {
				$out[] = [
					'key' => self::ParsingVar($key),
					'value' => self::ParsingVar($value)
				];
			}

			return $out;
		}

		private static function ParsingObject(object $obj): array {

			$parseModifiers = function (int $modifiers): array {
				$out = [];

				if ($modifiers & ReflectionClass::IS_IMPLICIT_ABSTRACT) {						// PHP >= 7.4.0
					$out[] = 'abstract';
					$out[] = 'implicit';
				}
				if ($modifiers & ReflectionClass::IS_EXPLICIT_ABSTRACT) {						// PHP >= 7.4.0
					$out[] = 'abstract';
					$out[] = 'explicit';
				}
				if ($modifiers & ReflectionClass::IS_FINAL) $out[] = 'final';					// PHP >= 7.4.0
//				if ($modifiers & ReflectionClass::IS_READONLY) $out[] = 'readonly';				// PHP >= 8.2.0

				return $out;
			};

			$reflection = new ReflectionClass($obj);

			return [
				'namespace' => $reflection->getNamespaceName(),
				'name' => $reflection->getShortName(),
				'modifiers' => $parseModifiers($reflection->getModifiers()),
				'constants' => self::getObjectConstants($reflection),
				'properties' => self::getObjectProperties($reflection, $obj),
				'methods' => self::getObjectMethods($reflection),
			];
		}

		private static function getObjectConstants(ReflectionClass $reflection): array {

			$parseModifiers = function (int $modifiers): array {
				$out = [];

				if ($modifiers & ReflectionClassConstant::IS_PUBLIC) $out[] = 'public';			// PHP >= 7.4.0
				if ($modifiers & ReflectionClassConstant::IS_PROTECTED) $out[] = 'protected';	// PHP >= 7.4.0
				if ($modifiers & ReflectionClassConstant::IS_PRIVATE) $out[] = 'private';		// PHP >= 7.4.0
//				if ($modifiers & ReflectionClassConstant::IS_FINAL) $out[] = 'final';			// PHP >= 8.1.0

				return $out;
			};

			$out = [];
			$constants = $reflection->getConstants();
			foreach ($constants as $name => $value) {
				$reflectionConstant = $reflection->getReflectionConstant($name);

				$modifiers		= $parseModifiers($reflectionConstant->getModifiers());
				$name			= $reflectionConstant->getName();
				$value			= self::ParsingVar($reflectionConstant->getValue());

				$out[] = compact('modifiers', 'name', 'value');
			}

			return $out;
		}

		private static function getObjectProperties(ReflectionClass $reflection, $obj): array {

			$parseModifiers = function (int $modifiers): array {
				$out = [];

				if ($modifiers & ReflectionProperty::IS_PUBLIC) $out[] = 'public';				// PHP >= 7.4.0
				if ($modifiers & ReflectionProperty::IS_PROTECTED) $out[] = 'protected';		// PHP >= 7.4.0
				if ($modifiers & ReflectionProperty::IS_PRIVATE) $out[] = 'private';			// PHP >= 7.4.0
				if ($modifiers & ReflectionProperty::IS_STATIC) $out[] = 'static';				// PHP >= 7.4.0
//				if ($modifiers & ReflectionProperty::IS_READONLY) $out[] = 'readonly';			// PHP >= 8.1.0

				return $out;
			};

			$out = [];
			$properties = $reflection->getProperties();
			foreach ($properties as $property) {
				$reflectionProperty = $reflection->getProperty($property->name);
				$reflectionProperty->setAccessible(true);

				$modifiers		= $parseModifiers($reflectionProperty->getModifiers());
				$name			= $reflectionProperty->getName();
				$value			= self::ParsingVar($reflectionProperty->getValue($property->isStatic() ? null : $obj));

				$out[] = compact('modifiers', 'name', 'value');
			}

			return $out;
		}

		private static function getObjectMethods(ReflectionClass $reflection): array {

			$parseModifiers = function (int $modifiers): array {
				$out = [];

				if ($modifiers & ReflectionMethod::IS_PUBLIC) $out[] = 'public';				// PHP >= 7.4.0
				if ($modifiers & ReflectionMethod::IS_PROTECTED) $out[] = 'protected';			// PHP >= 7.4.0
				if ($modifiers & ReflectionMethod::IS_PRIVATE) $out[] = 'private';				// PHP >= 7.4.0
				if ($modifiers & ReflectionMethod::IS_FINAL) $out[] = 'final';					// PHP >= 7.4.0
				if ($modifiers & ReflectionMethod::IS_STATIC) $out[] = 'static';				// PHP >= 7.4.0
				if ($modifiers & ReflectionMethod::IS_ABSTRACT) $out[] = 'abstract';			// PHP >= 7.4.0

				return $out;
			};

			$out = [];
			$methods = $reflection->getMethods();
			foreach ($methods as $method) {
				$reflectionMethod = $reflection->getMethod($method->name);

				$modifiers		= $parseModifiers($reflectionMethod->getModifiers());
				$name 			= $reflectionMethod->getName();

				$out[] = compact('modifiers', 'name');
			}

			return $out;
		}

	}